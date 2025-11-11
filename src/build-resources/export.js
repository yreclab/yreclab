if (typeof YREC !== 'undefined') {
  YREC.onRuntimeInitialized = () => {
  console.log("YREC runtime initialized");
  self.postMessage("ready|");
};

}
if (typeof module !== 'undefined' && module.exports) {
  module.exports = YREC;
}
