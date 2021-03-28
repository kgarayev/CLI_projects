var i = 0;
var text = "Here you learn how to become a Chartered Civil Engineer."
var speed = 70;

window.onload = function TypeWriter()
    {
        if(i < text.length)
        {
            document.getElementById("typing").innerHTML += text.charAt(i);
            i++;
            setTimeout(TypeWriter, speed);
        }


    }

