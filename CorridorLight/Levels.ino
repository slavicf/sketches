// WS2812 driver
void levels() {
  //  Serial.print("Level: ");
  if (timer0) {
    level++;
  } else {
    level--;
  }

  if (level < LEVEL_MIN) level = LEVEL_MIN;
  if (level > LEVEL_MAX) level = LEVEL_MAX;
  //  Serial.println(level);

  uint32_t color = level + (level << 8) + (level << 16);

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

