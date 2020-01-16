
bool bufPush(int value) {
  int temp = (bufHead + 1) & 0x1F;
  if(temp != bufTail) {
    bufHead = temp;
    buf[bufHead] = value;
    return true;
  } else {
    return false;
  }
}

int bufPull() {
  if(bufTail != bufHead) {
    bufTail = ++bufTail & 0x1F;
    return buf[bufTail];
  } else {
    return -1;
  }
}
