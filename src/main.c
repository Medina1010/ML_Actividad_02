#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct {
  int width, height, channels;
  unsigned char *data;
} stbi_image;

typedef struct {
  int x, y;
} Point;

void convolution_image(const stbi_image *image, const stbi_image *kernel,
                       stbi_image *result, int channels);
void substract_image(const stbi_image *image_1, const stbi_image *image_2,
                     stbi_image *result, int channels);
Point search_image(const stbi_image *image, const stbi_image *kernel,
                   stbi_image *result, int channels);
void stbi_load_simple(char *path, stbi_image *image, int channels);
void stbi_write_png_simple(char *path, stbi_image *image, int channels);
void draw_square(stbi_image *image, Point pos, Point dim, int channels);

int main(int argc, char **argv) {
  // selecting the number of channels: 1 -> gray_scale, 3 -> RGB, 4 -> RGBA
  int channels = 3;
  // loading the initial image
  stbi_image left_image;
  stbi_load_simple("res/left.png", &left_image, channels);
  stbi_image places_image;
  stbi_load_simple("res/left.png", &places_image, channels);
  stbi_image right_image;
  stbi_load_simple("res/right.png", &right_image, channels);

  stbi_image result;

  // doing the difference
  substract_image(&left_image, &right_image, &result, channels);
  stbi_write_png_simple("res/difference.png", &result, channels);
  stbi_image_free(result.data);
  printf("[%s]: done difference\n", argv[0]);

  stbi_image image_kernel;
  char str[256];
  for (int i = 1; i <= 5; i++) {
    // loading the kernel image
    sprintf(str, "res/Object-%d.png", i);
    stbi_load_simple(str, &image_kernel, channels);
    // doing the convolution
    convolution_image(&left_image, &image_kernel, &result, channels);
    // saving the result
    sprintf(str, "res/convolution-%d.png", i);
    stbi_write_png_simple(str, &result, channels);
    printf("[%s]: done the %d/5 convolution\n", argv[0], i);
    // cleaning the memory
    stbi_image_free(result.data);

    // doing the search and drawing square at the closest point
    draw_square(&places_image,
                search_image(&left_image, &image_kernel, &result, channels),
                (Point){image_kernel.width, image_kernel.height}, channels);
    sprintf(str, "res/search-%d.png", i);
    stbi_write_png_simple(str, &result, channels);
    printf("[%s]: done the %d/5 standard deviation\n", argv[0], i);
    // cleaning the memory
    stbi_image_free(result.data);

    stbi_image_free(image_kernel.data);
  }
  stbi_write_png_simple("res/places_image.png", &places_image, channels);

  stbi_image_free(places_image.data);
  stbi_image_free(left_image.data);
  stbi_image_free(right_image.data);

  return 0;
}

void draw_square(stbi_image *image, Point pos, Point dim, int channels) {
  for (int i = 0; i < dim.x; i++) {
    image->data[channels * (pos.x + i + image->width * pos.y)] = 255;
    image->data[channels * (pos.x + i + image->width * (pos.y + dim.y))] = 255;
    for (int j = 1; j < channels; j++) {
      image->data[channels * (pos.x + i + image->width * pos.y) + j] = 0;
      image->data[channels * (pos.x + i + image->width * (pos.y + dim.y)) + j] =
          0;
    }
  }
  for (int i = 0; i < dim.y; i++) {
    image->data[channels * (pos.x + image->width * (pos.y + i))] = 255;
    image->data[channels * (pos.x + dim.x + image->width * (pos.y + i))] = 255;
    for (int j = 1; j < channels; j++) {
      image->data[channels * (pos.x + image->width * (pos.y + i)) + j] = 0;
      image->data[channels * (pos.x + dim.x + image->width * (pos.y + i)) + j] =
          0;
    }
  }
}

Point search_image(const stbi_image *image, const stbi_image *kernel,
                   stbi_image *result, int channels) {
  // creating room for the result
  result->width = (image->width - kernel->width + 1);
  result->height = (image->height - kernel->height + 1);
  result->data = malloc(result->width * result->height * channels);
  int x, y, max = 0;
  float accumulator, average;
  // through the image
  for (int j = 0; j < result->height; j++) {
    for (int i = 0; i < result->width; i++) {
      // through the channels
      for (int c = 0; c < channels; c++) {
        // through the kernel
        accumulator = 0;
        for (int kj = 0; kj < kernel->height; kj++) {
          for (int ki = 0; ki < kernel->width; ki++) {
            accumulator += pow(
                (int)(image
                          ->data[channels * (i + ki + image->width * (j + kj)) +
                                 c]) -
                    (int)(kernel
                              ->data[channels * (ki + kernel->width * kj) + c]),
                2);
          }
        }
        result->data[channels * (i + result->width * j) + c] =
            255 -
            (unsigned char)sqrt(accumulator / (kernel->width * kernel->height));
        average += result->data[channels * (i + result->width * j) + c];
      }
      if (average > max) {
        x = i;
        y = j;
        max = average;
      }
      average = 0;
    }
  }
  return (Point){x, y};
};

void convolution_image(const stbi_image *image, const stbi_image *kernel,
                       stbi_image *result, int channels) {
  // creating room for the result
  result->width = (image->width - kernel->width + 1);
  result->height = (image->height - kernel->height + 1);
  result->data = malloc(result->width * result->height * channels);
  // count to normalize to 255
  int count[channels];
  for (int c = 0; c < channels; c++) {
    count[c] = 0;
    for (int i = 0; i < kernel->width * kernel->height; i++)
      count[c] += kernel->data[i * channels + c];
  }
  float accumulator;
  // through the image
  for (int j = 0; j < result->height; j++) {
    for (int i = 0; i < result->width; i++) {
      // through the channels
      for (int c = 0; c < channels; c++) {
        // through the kernel
        accumulator = 0;
        for (int kj = 0; kj < kernel->height; kj++) {
          for (int ki = 0; ki < kernel->width; ki++) {
            accumulator +=
                (int)(image
                          ->data[channels * (i + ki + image->width * (j + kj)) +
                                 c]) *
                (int)(kernel->data[channels * (ki + kernel->width * kj) + c]);
          }
        }
        result->data[channels * (i + result->width * j) + c] =
            (unsigned char)(accumulator / (count[c]));
      }
    }
  }
};

void substract_image(const stbi_image *image_1, const stbi_image *image_2,
                     stbi_image *result, int channels) {
  if (image_1->width != image_2->width || image_1->height != image_2->height)
    return;
  result->width = image_1->width;
  result->height = image_1->height;
  result->data = malloc(result->width * result->height * channels);
  for (int i = 0; i < result->width * result->height * channels; i++) {
    result->data[i] = abs((int)image_1->data[i] - (int)image_2->data[i]);
  }
}

void stbi_load_simple(char *path, stbi_image *image, int channels) {
  image->data = stbi_load(path, &image->width, &image->height, &image->channels,
                          channels);
}

void stbi_write_png_simple(char *path, stbi_image *image, int channels) {
  stbi_write_png(path, image->width, image->height, channels, image->data,
                 image->width * channels);
}
