document.addEventListener('DOMContentLoaded', function () {
    //console.log('setugIOS');
    locuslabs.setupIOS(function () {
        //console.log('setup complete');

        // Stupid hacks to get iOS to pass touch events.  I have no idea why this works.
        document.getElementsByTagName("body")[0].addEventListener("touchstart",function(){});
        document.getElementsByTagName("body")[0].addEventListener("touchend",function(){});
        document.getElementsByTagName("body")[0].addEventListener("touchmove",function(){});

        locuslabs.ios.setup();
    });
});