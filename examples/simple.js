function echo() {
    console.log("echo ok");
}

function fetchFile(path) {
    var doneCallback = function(txt) {
        console.log(md5(txt));
    }

    var errorCallback = function(txt) {
        console.warn(txt);
    }

    var f = new Fetcher(path);
    f.done.connect(doneCallback);
    f.error.connect(errorCallback);
    f.fetch();
}

//fetchFile(appInstallPath + "/../qtupdater/examples/simple.js");

fetchFile(appInstallPath + "/qtupdater");
