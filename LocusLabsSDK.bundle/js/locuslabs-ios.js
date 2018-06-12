var ios;

locuslabs.setupIOS = function (callback) {
    if (typeof ios === 'undefined') {
        ios = {
            ready : function () {
                window.webkit.messageHandlers.ready.postMessage('ready')
            },
            callFunction : function (uuid,json) {
                window.webkit.messageHandlers.callFunction.postMessage({uuid, json})
            },
            eventRelay : {
                submit : function (event) {
                    var eventString = JSON.stringify(event);
                    window.webkit.messageHandlers.event.postMessage(eventString)
                }
            }
        };
    }
    // Redirect JS logging to iOS
    console = console || {};
    // see https://stackoverflow.com/a/11403146 for explanation:
    (function(){
        var oldLog = console.log;
        console.log = function( log ) {
            // send to iOS
            window.webkit.messageHandlers.log.postMessage(log)
            // invoke the original method to print the log in JS console
            oldLog.apply(console, arguments)
        };
    })();
    console.debug = console.log;
    console.info = console.log;
    console.warn = console.log;

    locuslabs.iosSetupCallback = function () {
        locuslabs.ios = new locuslabs.Native( ios );

        console.error = console.log;

        // Use the native iOS panzoom mechanism
        locuslabs.config[ 'panZoomMethod' ] = 'iosScrollView';

        callback();
    };
    window.webkit.messageHandlers.setup.postMessage('setup')
    // ios.execute( 'ios-setup://' );
};
