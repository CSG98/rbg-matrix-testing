#include "led-matrix.h"
#include "graphics.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <string>
#include <time.h>


using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void Number1 (int xpos){
 rgb_matrix::Drawline(canvas, xpos+1, ypos, xpos+1, ypos+4, &green);
 rgb_matrix:SetPixel(xpos, ypos+1, 0, 255, 0);
 rgb_matrix::Drawline(canvas, xpos, ypos+8, xpos+2, ypos+8, &green);
}

void Number2 (int xpos){
  rgb_matrix:SetPixel(xpos+1, ypos, 0, 255, 0);
  rgb_matrix:SetPixel(xpos, ypos+1, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos+2, ypos+1, xpos+2, ypos+2, &green);
  rgb_matrix:SetPixel(xpos+1, ypos+3, 0, 255, 0);
  rgb_matrix:SetPixel(xpos, ypos+8, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos, ypos+9, xpos+2, ypos+9, &green);
}
void Number3 (int xpos){
  rgb_matrix::Drawline(canvas, xpos, ypos, xpos+1, ypos, &green);
  rgb_matrix:SetPixel(xpos+2, ypos+1, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos, ypos+2, xpos+1, ypos+2, &green);
  rgb_matrix::Drawline(canvas, xpos+2, ypos+3, xpos+2, ypos+8, &green);
  rgb_matrix::Drawline(canvas, xpos, ypos+9, xpos+1, ypos+9, &green);
}

void Number4 (int xpos){
  rgb_matrix::SetPixel(xpos+2, ypos, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos+1, ypos+1, xpos+2, ypos+1, &green);
  rgb_matrix::Drawline(canvas, xpos, ypos+2, xpos, ypos+3, &green);
  rgb_matrix::Drawline(canvas, xpos+1, ypos+3, xpos+2, ypos+3, &green);
  rgb_matrix::SetPixel(xpos+2, ypos+2, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+2, ypos+8, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+2, ypos+9, 0, 255, 0);
}

void Number5 (int xpos){
  rgb_matrix::Drawline(canvas, xpos, ypos, xpos+2, ypos, &green);
  rgb_matrix::Drawline(canvas, xpos, ypos+1, xpos, ypos+2, &green);
  rgb_matrix::Drawline(canvas, xpos, ypos+2, xpos+2, ypos+2, &green);
  rgb_matrix::SetPixel(xpos+2, ypos+3, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+2, ypos+8, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos, ypos+9, xpos+1, ypos+9, &green);
}

void Number6 (int xpos){
 rgb_matrix::Drawline(canvas, xpos+1, ypos, xpos+2, ypos, &green);
 rgb_matrix::SetPixel(xpos+1, ypos+3, 0, 255, 0);
 rgb_matrix::SetPixel(xpos+2, ypos+8, 0, 255, 0);
 rgb_matrix::Drawline(canvas, xpos, ypos+1, xpos, ypos+3, &green);
 rgb_matrix::SetPixel(xpos, ypos+8, 0, 255, 0);
 rgb_matrix::SetPixel(xpos+1, ypos+9, 0, 255, 0);
}
void Number7 (int xpos, int ypos){
 rgb_matrix::Drawline(canvas, xpos, ypos, xpos+1, ypos, &green);
 rgb_matrix::Drawline(canvas, xpos+2, ypos, xpos+2, ypos+1, &green);
 rgb_matrix::Drawline(canvas, xpos+1, ypos+2, xpos+1, ypos+3, &green);
 rgb_matrix::Drawline(canvas, xpos+1, ypos+8, xpos+1, ypos+9, &green);
}

void Number8 (int xpos, int ypos){
  rgb_matrix::SetPixel(xpos+1, ypos, 0, 255, 0);
  rgb_matrix::SetPixel(xpos, ypos+1, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+2, ypos+2, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+1, ypos+3, 0, 255, 0);
  rgb_matrix::SetPixel(xpos, ypos+8, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+2, ypos+8, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+1, ypos+9, 0, 255, 0);
}
void Number9 (int xpos, int ypos){
  rgb_matrix::Drawline(canvas, xpos, ypos, xpos+2, ypos, &green);
  rgb_matrix::SetPixel(xpos, ypos+1, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos, ypos+2, xpos+1, ypos+2, &green);
  rgb_matrix::Drawline(canvas, xpos+2, ypos+1, xpos+2, ypos+3, &green);
  rgb_matrix::Drawline(canvas, xpos+2, ypos+8, xpos+2, ypos+9, &green);
}

void Number0 (int xpos, int ypos){
  rgb_matrix::SetPixel(xpos+1, ypos, 0, 255, 0);
  rgb_matrix::Drawline(canvas, xpos, ypos+1, xpos, ypos+3, &green);
  rgb_matrix::Drawline(canvas, xpos+2, ypos+1, xpos+2, ypos+3, &green);
  rgb_matrix::SetPixel(xpos+2, ypos+8, 0, 255, 0);
  rgb_matrix::SetPixel(xpos, ypos+8, 0, 255, 0);
  rgb_matrix::SetPixel(xpos+1, ypos+9, 0, 255, 0);
}

static int usage(const char *progname) {
  fprintf(stderr, "usage: %s [options]\n", progname);
  fprintf(stderr, "Reads text from stdin and displays it. "
          "Empty string: clear screen\n");
  fprintf(stderr, "Options:\n");
  fprintf(stderr,
          "\t-x <x-origin>     : X-Origin of displaying text (Default: 0)\n"
          "\t-y <y-origin>     : Y-Origin of displaying text (Default: 0)\n"
          "\t-C <r,g,b>        : Color. Default 255,255,0\n"
          "\t-F <r,g,b>        : Panel flooding-background color. Default 0,0,0\n"
          "\n"
          );
  rgb_matrix::PrintMatrixFlags(stderr);
  return 1;
}

static bool parseColor(Color *c, const char *str) {
  return sscanf(str, "%hhu,%hhu,%hhu", &c->r, &c->g, &c->b) == 3;
}

static bool FullSaturation(const Color &c) {
  return (c.r == 0 || c.r == 255)
    && (c.g == 0 || c.g == 255)
    && (c.b == 0 || c.b == 255);
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options matrix_options;
  rgb_matrix::RuntimeOptions runtime_opt;
  if (!rgb_matrix::ParseOptionsFromFlags(&argc, &argv,
                                         &matrix_options, &runtime_opt)) {
    return usage(argv[0]);
  }

  Color color(255, 255, 255);
  Color green(0,255,0);
  Color bg_color(0, 0, 0);
  Color flood_color(0, 0, 0);
  bool with_outline = false;

  const char *bdf_font_file = NULL;
  int x_orig = 0;
  int y_orig = 0;
  int letter_spacing = 0;

  int opt;
  while ((opt = getopt(argc, argv, "x:y:C:B:F:")) != -1) {
    switch (opt) {
    case 'x': x_orig = atoi(optarg); break;
    case 'y': y_orig = atoi(optarg); break;
    case 'C':
      if (!parseColor(&color, optarg)) {
        fprintf(stderr, "Invalid color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    case 'B':
      if (!parseColor(&bg_color, optarg)) {
        fprintf(stderr, "Invalid background color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    case 'F':
      if (!parseColor(&flood_color, optarg)) {
        fprintf(stderr, "Invalid background color spec: %s\n", optarg);
        return usage(argv[0]);
      }
      break;
    default:
      return usage(argv[0]);
    }
  }



  RGBMatrix *canvas = RGBMatrix::CreateFromOptions(matrix_options, runtime_opt);
  if (canvas == NULL)
    return 1;

  const bool all_extreme_colors = (matrix_options.brightness == 100)
    && FullSaturation(color)
    && FullSaturation(bg_color)
    && FullSaturation(outline_color);
  if (all_extreme_colors)
    canvas->SetPWMBits(1);

  const int x = x_orig;
  int y = y_orig;

  if (isatty(STDIN_FILENO)) {
    // Only give a message if we are interactive. If connected via pipe, be quiet
    printf("Enter lines. Full screen or empty line clears screen.\n"
           "Supports UTF-8. CTRL-D for exit.\n");
  }

  canvas->Fill(flood_color.r, flood_color.g, flood_color.b);
  char line[1024];
  while (fgets(line, sizeof(line), stdin)) {
    const size_t last = strlen(line);
    if (last > 0) line[last - 1] = '\0';  // remove newline.
    bool line_empty = strlen(line) == 0;
    if ((y + font.height() > canvas->height()) || line_empty) {
      canvas->Fill(flood_color.r, flood_color.g, flood_color.b);
      y = y_orig;
    }
    if (line_empty)
      continue;
  }
  //S for score
  rgb_matrix::Drawline(canvas, 1, 0, 3, 0, &color);
  rgb_matrix::SetPixel(0, 1, 255, 255, 255);
  rgb_matrix::SetPixel(1, 2, 255, 255, 255);
  rgb_matrix::SetPixel(2, 3, 255, 255, 255);
  rgb_matrix::Drawline(canvas, 0, 8, 1, 8, &color);
//c
  rgb_matrix::Drawline(canvas, 4, 1, 6, 1, &color);
  rgb_matrix::Drawline(canvas, 4, 2, 4, 3, &color);
  rgb_matrix::Drawline(canvas, 5, 8, 6, 8, &color);

//o
  rgb_matrix::SetPixel(9, 1, 255, 255, 255);
  rgb_matrix::Drawline(canvas, 8, 2, 8, 3, &color);
  rgb_matrix::Drawline(canvas, 10, 2, 10, 3, &color);
  rgb_matrix::SetPixel(9, 8, 255, 255, 255);

//r
  rgb_matrix::Drawline(canvas, 12, 1, 12, 3, &color);
  rgb_matrix::SetPixel(13, 2, 255, 255, 255);
  rgb_matrix::SetPixel(14, 1, 255, 255, 255);
  rgb_matrix::SetPixel(12, 8, 255, 255, 255);
 
 //e
  rgb_matrix::Drawline(canvas, 17, 8, 18, 8, &color);
  rgb_matrix::SetPixel(18, 2, 255, 255, 255);
  rgb_matrix::SetPixel(17, 1, 255, 255, 255);
  rgb_matrix::SetPixel(17, 3, 255, 255, 255);
  rgb_matrix::Drawline(canvas, 16, 2, 16, 3, &color);

//9 : 9

  Number9(70, 0);
  rgb_matrix::SetPixel(74, 1, 0, 255, 0);
  rgb_matrix::SetPixel(74, 3, 0, 255, 0);
  Number9(76,0);

 /*
 char text_buffer[256];
  struct timespec next_time;
  next_time.tv_sec = time(NULL);
  next_time.tv_nsec = 0;
  struct tm tm;

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  while (!interrupt_received) {
    offscreen->Fill(bg_color.r, bg_color.g, bg_color.b);
    localtime_r(&next_time.tv_sec, &tm);

    int line_offset = 0;
    for (const std::string &line : format_lines) {
      strftime(text_buffer, sizeof(text_buffer), line.c_str(), &tm);
      if (outline_font) {
        rgb_matrix::DrawText(offscreen, *outline_font,
                             x - 1, y + font.baseline() + line_offset,
                             outline_color, NULL, text_buffer,
                             letter_spacing - 2);
      }
      rgb_matrix::DrawText(offscreen, font,
                           x, 33,
                           color, NULL, text_buffer,
                           letter_spacing);
      line_offset += font.height() + line_spacing;
    }

    // Wait until we're ready to show it.
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &next_time, NULL);

    // Atomic swap with double buffer
    offscreen = matrix->SwapOnVSync(offscreen);

    next_time.tv_sec += 1;
  }
*/
  // Finished. Shut down the RGB matrix.
  delete canvas;

  return 0;
}
