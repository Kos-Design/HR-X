

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}
//I'm joking somehow, best to derive that from an isEven module
void toggle_that(bool &booler){
  booler = !booler;
}

