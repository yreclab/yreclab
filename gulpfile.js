const gulp = require('gulp')
const shell = require('gulp-shell')
const libf2cFiles = require('./build-resources/libf2c-files')
const yrecFiles = require('./build-resources/yrec-files')
const blasFiles = require('./build-resources/blas-files')
const lapackFiles = require('./build-resources/lapack-files')
const exportFunctions = require('./build-resources/export-functions')

const lapackInstallFiles = [
  'dlamch',
  'slamch'
]

var joinNames = function (names) {
  return names
    .map(function (name) {
      return '"' + name + '"'
    })
    .join(',')
}

gulp.task('mkbuild', shell.task(['mkdir -p build']))

gulp.task('compile-libf2c', ['mkbuild'], shell.task(
  libf2cFiles.map(function (name) {
    return 'emcc CLAPACK-3.2.1/F2CLIBS/libf2c/' + name + '.c -O3 -ICLAPACK-3.2.1/INCLUDE -o build/' + name + '.bc'
  })
))

gulp.task('compile-lapack-install', ['mkbuild'], shell.task(
  lapackInstallFiles
    .map(function (name) {
      return 'emcc CLAPACK-3.2.1/INSTALL/' + name + '.c -O3 -ICLAPACK-3.2.1/INCLUDE -o build/' + name + '.bc'
    })
))

gulp.task('compile-lapack', ['mkbuild'], shell.task(
  lapackFiles
    .map(function (name) {
      return 'emcc CLAPACK-3.2.1/SRC/' + name + '.c -O3 -ICLAPACK-3.2.1/INCLUDE -o build/' + name + '.bc'
    })
))

gulp.task('compile-yrec', ['mkbuild'], shell.task(
  yrecFiles
    .map(function (name) {
      return 'emcc ' + name + '.c -O3 -ICLAPACK-3.2.1/INCLUDE -o build/' + name + '.bc'
    })
))

gulp.task('link-asmjs', [], shell.task([//['compile-libf2c', 'compile-lapack', 'compile-lapack-install', 'compile-yrec'], shell.task([
  "emcc build/*.bc -o asmjs.js -O0 --memory-init-file 0 -s TOTAL_MEMORY=134217728 --embed-file yrec8.nml1 --embed-file yrec8.nml2 --embed-file input --embed-file output -s EXPORTED_FUNCTIONS='[" + joinNames(exportFunctions) + "]' --post-js build-resources/export.js"
]))

gulp.task('link-wasm', [], shell.task([//['compile-libf2c', 'compile-lapack', 'compile-lapack-install', 'compile-yrec'], shell.task([
  "emcc build/*.bc -o wasm.js -O3 --memory-init-file 0 -s TOTAL_MEMORY=134217728 --embed-file yrec8.nml1 --embed-file yrec8.nml2 --embed-file input --embed-file output -s WASM=1 -s EXPORTED_FUNCTIONS='[" + joinNames(exportFunctions) + "]' --post-js build-resources/export.js"
]))

gulp.task('link-yrec-html', [], shell.task([//['compile-libf2c', 'compile-lapack', 'compile-lapack-install', 'compile-yrec'], shell.task([
  "emcc build/*.bc -o yrec.html -O3 --memory-init-file 0 -s WASM=1 -s TOTAL_MEMORY=201326592 --preload-file yrec8.nml1 --preload-file yrec8.nml2 --preload-file input --preload-file output -s EXPORTED_FUNCTIONS='[" + joinNames(exportFunctions) + "]' --post-js build-resources/export.js"
]))

gulp.task('build', ['link-wasm', 'link-yrec-html'])

gulp.task('test', shell.task('mocha --recursive --colors --reporter dot'))

gulp.task('default', ['build'])
