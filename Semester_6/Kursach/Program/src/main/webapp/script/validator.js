let form = document.querySelector('.js-form'),
    formInputs = document.querySelectorAll('.js-input');

form.onsubmit = function () {
    let emptyInputs = Array.from(formInputs).filter(input => input.value === '');

    formInputs.forEach(function (input) {
        if (input.value === '') {
            input.classList.add('error');
        } else {
            input.classList.remove('error');
        }
    })

    return emptyInputs.length === 0;
}

