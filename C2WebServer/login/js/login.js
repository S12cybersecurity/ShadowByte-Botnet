document.addEventListener('DOMContentLoaded', function() {
    console.log('Login Page');
    const userValue = document.getElementById('userBox');
    const passwdValue = document.getElementById('passwordBox');
    const buttom = document.getElementById('button');
    const toast = document.getElementById('toast');

    function buttomClick(){
        if(userValue.value === '' || passwdValue.value === ''){
            toast.innerText = 'One or more field are empty';
            toast.classList.add('show');
            setTimeout(function(){ toast.classList.remove('show'); }, 4000);
        }else{
        }
    }

    buttom.onclick = buttomClick;

});