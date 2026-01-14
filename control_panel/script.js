const command_input = document.getElementById('input');
const output = document.getElementById('output')
command_input.addEventListener('keypress', function(event) {
    if (event.key === 'Enter') {
        command = command_input.value;
        console.log('Command entered:', command);
        command_input.value = '';
        if (command === 'clear') {
            output.innerHTML = '>';
            console.clear;
        }
        else {
            output.innerHTML += '>' + command + '<br>';
            output.scrollTop = output.scrollHeight;
        }
        
    }
}
)