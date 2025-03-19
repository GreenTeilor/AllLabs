const socket = io('/main');

function handleAiGameBtnClick() {
    //No additional actions
}

function handleMultiplayerBtnClick() {
    socket.emit('multiplayer-game-desire-event');

    //Start timer
    const timer = document.getElementById('timer');
    timer.classList.remove('hidden');
    let startTime = Date.now();
    const updateTimer = () => {
        const elapsedTime = Math.floor((Date.now() - startTime) / 1000);
        timer.innerText = `${elapsedTime}`;
    };
    setInterval(() => {
        updateTimer();
    }, 1000);
}

socket.on('game-found-event', (gameInfo) => {
    window.location.replace(`/game/multiplayer?color=${gameInfo.color}&gameId=${gameInfo.gameId}`);
})