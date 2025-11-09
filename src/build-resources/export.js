if (typeof Module !== 'undefined') {
  Module.onRuntimeInitialized = () => {
  // libf2c runtime setup
  if (Module._f_init) Module._f_init();

  console.log("YREC runtime initialized");

  // Now call your translated Fortran entry
  const rc = Module._MAIN__();
  console.log("YREC finished with code:", rc);

  if (Module._f_exit) Module._f_exit();
};

}
if (typeof module !== 'undefined' && module.exports) {
  module.exports = Module;
}
