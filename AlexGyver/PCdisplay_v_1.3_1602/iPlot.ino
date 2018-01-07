
void updatePlot() {
  if ((millis() - plot_timer) > (PCdata[17] * 1000)) {
    for (int i = 0; i < 6; i++) {           // для каждой строки параметров
      for (int j = 0; j < 15; j++) {        // каждый столбец параметров (кроме последнего)
        PLOTmem[i][j] = PLOTmem[i][j + 1];  // сдвинуть весь массив на шаг ВЛЕВО
      }
    }
    for (int i = 0; i < 6; i++) {
      // запомнить общее число полосок графика в ПОСЛЕДНИЙ элемент массива
      PLOTmem[i][15] = PCdata[plotLines[i]];
    }
    plot_timer = millis();
  }
}

