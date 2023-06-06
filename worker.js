var module={};

var Module = {
    preRun:[],
    onRuntimeInitialized: function load_done_callback() {
        console.info("The Module is loaded and is accessible here", Module);
        self.postMessage("ready|");
    },
    YREC_return_val: -1,
};

importScripts('yrec.js');

self.addEventListener('message', function(e) {
if (e.data == 'run' && Module.onRuntimeInitialized && Module.YREC_return_val == -1){
	while(Module.YREC_return_val == -1){
		Module.YREC_return_val = Module._MAIN__();
		self.postMessage("track|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.track')));
		self.postMessage("full|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.full')));
		self.postMessage("short|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.short')));
		self.postMessage("store|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.store')));
		self.postMessage("last|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.last')));
	}
}
else if (e.data == 'chain' && Module.onRuntimeInitialized && Module.YREC_return_val == -1){
	Module.YREC_return_val = Module._MAIN__();
	self.postMessage("track|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.track')));
	self.postMessage("full|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.full')));
	self.postMessage("short|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.short')));
	self.postMessage("store|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.store')));
	self.postMessage("last|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.last')));
	self.postMessage("chain|");
}
else if (e.data == 'step' && Module.onRuntimeInitialized && Module.YREC_return_val == -1){
	Module.YREC_return_val = Module._MAIN__();
	self.postMessage("track|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.track')));
	self.postMessage("full|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.full')));
	self.postMessage("short|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.short')));
	self.postMessage("store|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.store')));
	self.postMessage("last|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.last')));
}
else if (e.data == 'get_track' && Module.onRuntimeInitialized){
	self.postMessage("track|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.track')));
}
else if (e.data == 'get_full' && Module.onRuntimeInitialized){
	self.postMessage("full|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.full')));
}
else if (e.data == 'get_short' && Module.onRuntimeInitialized){
	self.postMessage("short|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.short')));
}
else if (e.data == 'get_store' && Module.onRuntimeInitialized){
	self.postMessage("store|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.store')));
}
else if (e.data == 'get_last' && Module.onRuntimeInitialized){
	self.postMessage("last|"+new TextDecoder().decode(FS.readFile('output/solarmodel/m100gs98difmod4p61sfiinewrc.last')));
}
else if (e.data.split("|")[0] == "set_nml1" && Module.onRuntimeInitialized){
	var yrec8_nml1_string_out = e.data.split("|")[1];
	var yrec8_nml1_binary_out = new TextEncoder().encode(yrec8_nml1_string_out);
	FS.writeFile('yrec8.nml1', yrec8_nml1_binary_out);
	var yrec8_nml1_binary_in = FS.readFile('yrec8.nml1');
	var nml1_str = new TextDecoder().decode(yrec8_nml1_binary_in);
	self.postMessage("nml1|"+nml1_str);
}
else if (e.data.split("|")[0] == "set_nml2" && Module.onRuntimeInitialized){
	var yrec8_nml2_string_out = e.data.split("|")[1];
	var yrec8_nml2_binary_out = new TextEncoder().encode(yrec8_nml2_string_out);
	FS.writeFile('yrec8.nml2', yrec8_nml2_binary_out);
	var yrec8_nml2_binary_in = FS.readFile('yrec8.nml2');
	var nml2_str = new TextDecoder().decode(yrec8_nml2_binary_in);
	self.postMessage("nml2|"+nml2_str);
}
else if (e.data.split("|")[0] == "get_nml1" && Module.onRuntimeInitialized){
	var yrec8_nml1_binary_in = FS.readFile('yrec8.nml1');
	var nml1_str = new TextDecoder().decode(yrec8_nml1_binary_in);
	self.postMessage("nml1|"+nml1_str);
}
else if (e.data.split("|")[0] == "get_nml2" && Module.onRuntimeInitialized){
	var yrec8_nml2_binary_in = FS.readFile('yrec8.nml2');
	var nml2_str = new TextDecoder().decode(yrec8_nml2_binary_in);
	self.postMessage("nml2|"+nml2_str);
}
}, false);

