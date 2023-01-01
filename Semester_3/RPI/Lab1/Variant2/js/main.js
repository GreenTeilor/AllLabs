var scroll_distance = 900;
var transparent = true;
document.addEventListener("scroll", function() {
  if ($(document).scrollTop() > scroll_distance) {
    if (transparent) {
      transparent = false;
      $('.navbar').addClass('changeColor');
    }
  } else {
    if (!transparent) {
      transparent = true;
      $('.navbar').removeClass('changeColor');
    }
  }
});