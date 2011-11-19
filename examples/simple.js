function echo() {
    console.log("echo ok");
}

function fetchFile(path) {
    var doneCallback = function(txt) {
        console.log(txt);
        quit();
    }

    var errorCallback = function(txt) {
        console.warn(txt);
        quit();
    }

    var f = new Fetcher(path);
    f.done.connect(doneCallback);
    f.error.connect(errorCallback);
    f.fetch();
}

fetchFile("http://tools.ietf.org/rfc/rfc1321.txt");

//fetchFile(appInstallPath + "/qtupdater");
