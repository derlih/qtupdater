function echo() {
    console.log("echo ok");
}

function fetchScript() {
    var doneCallback = function(txt) {
        console.log(txt);
    }

    var errorCallback = function(txt) {
        console.warn(txt);
    }

    var f = new Fetcher("file:///home/mitya/Sources/qtupdater/examples/simple.js");
    f.done.connect(doneCallback);
    f.error.connect(errorCallback);
    f.fetch();
}

fetchScript();
