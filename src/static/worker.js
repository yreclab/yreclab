// worker.js
importScripts('yrec.js');

let yrecModule;
let yrecReturn = -1;

(async () => {
  const config = {
    preRun: [],
    onRuntimeInitialized() {
      console.info("YREC initialized.");
      self.postMessage("ready|");
    },
  };

  yrecModule = await YREC(config);
})();

self.addEventListener('message', async (e) => {
    if (!yrecModule) {
        console.warn("Module not ready yet");
        return;
    }

    const msg = e.data;

    if (msg === 'run') {
        while (yrecModule.YREC_return_val === -1) {
            yrecModule.YREC_return_val = yrecModule._step_();
            sendOutputs("run");
        }
    } else if (msg === 'chain') {
        yrecModule.YREC_return_val = yrecModule._step_();
        sendOutputs("chain");
        self.postMessage("chain|");
    } else if (msg === 'step') {
        yrecModule.YREC_return_val = yrecModule._step_();
        sendOutputs("step");
    }

    else if (msg === 'get_track') self.postMessage("track|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.track"));
    else if (msg === 'get_full')  self.postMessage("full|"  + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.full"));
    else if (msg === 'get_short') self.postMessage("short|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.short"));
    else if (msg === 'get_store') self.postMessage("store|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.store"));
    else if (msg === 'get_last')  self.postMessage("last|"  + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.last"));

    else if (msg.startsWith("set_nml1|")) {
        const data = msg.split("|")[1];
        yrecModule.FS.writeFile("yrec8.nml1", new TextEncoder().encode(data));
        self.postMessage("nml1|" + readFileSafe("yrec8.nml1"));
    } else if (msg.startsWith("set_nml2|")) {
        const data = msg.split("|")[1];
        yrecModule.FS.writeFile("yrec8.nml2", new TextEncoder().encode(data));
        self.postMessage("nml2|" + readFileSafe("yrec8.nml2"));
    } else if (msg.startsWith("get_nml1")) {
        self.postMessage("nml1|" + readFileSafe("yrec8.nml1"));
    } else if (msg.startsWith("get_nml2")) {
        self.postMessage("nml2|" + readFileSafe("yrec8.nml2"));
    }
}, false);

function readFileSafe(path) {
    try {
        return new TextDecoder().decode(yrecModule.FS.readFile(path));
    } catch (e) {
        console.warn(`Missing file: ${path}`);
        return "";
    }
}

function sendOutputs(tag) {
    self.postMessage("track|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.track"));
    self.postMessage("full|"  + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.full"));
    self.postMessage("short|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.short"));
    self.postMessage("store|" + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.store"));
    self.postMessage("last|"  + readFileSafe("output/solarmodel/m100gs98difmod4p61sfiinewrc.last"));
}
