

int fakeselector(float smallv, int maxrange) {
  return round(map(smallv, 0, 1, 0, maxrange));
}
//I'm joking somehow
void toggle_that(bool &booler){
  booler = !booler;
}