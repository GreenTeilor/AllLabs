var scroll_distance = 850;
var transparent = true;
document.addEventListener("scroll", function() {
  if ($(document).scrollTop() > scroll_distance) {
    if (transparent) {
      transparent = false;
      $('.container-nav').addClass('changeColor');
      $('.container-nav').addClass('addPaddings');
    }
  } else {
    if (!transparent) {
      transparent = true;
      $('.container-nav').removeClass('changeColor');
      $('.container-nav').removeClass('addPaddings');
    }
  }
});