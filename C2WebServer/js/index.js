document.addEventListener('DOMContentLoaded', function() {
    const btn = document.getElementById('btnSend');
    const toast = document.getElementById('toast');

    function btnClick(){
        toast.innerText = 'Command Executed';
        toast.classList.add('show');
        setTimeout(function(){ toast.classList.remove('show'); }, 4000);
    }

    btn.onclick = btnClick; 

});     