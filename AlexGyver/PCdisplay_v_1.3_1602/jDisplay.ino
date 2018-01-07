
void updateDisplay() {
  if (updateDisplay_flag) {
    if (reDraw_flag) {
      lcd.clear();
      switch (display_mode) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: draw_plot_symb();
          break;
        case 6: draw_labels_11();
          break;
        case 7: draw_labels_12();
          break;
        case 8: draw_labels_21();
          break;
        case 9: draw_labels_22();
          break;
      }
      reDraw_flag = 0;
    }
    switch (display_mode) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5: draw_plot();
        break;
      case 6: draw_stats_11();
        break;
      case 7: draw_stats_12();
        break;
      case 8: draw_stats_21();
        break;
      case 9: draw_stats_22();
        break;
      case 50: debug();
        break;
    }
    updateDisplay_flag = 0;
  }
}

