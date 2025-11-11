if (typeof Module !== 'undefined') {
  Module.onRuntimeInitialized = () => {
  // libf2c runtime setup
  if (Module._f_init) Module._f_init();

  console.log("YREC runtime initialized");
};

}
if (typeof module !== 'undefined' && module.exports) {
  module.exports = Module;
}
