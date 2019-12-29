const input = require('./input')

function calcMass(input) {
  return input
    .map(mass => Math.floor(mass / 3) - 2)
    .reduce((prev, curr) => prev + curr, 0)
}

function main() {
  const response = calcMass(input)
  console.log(`Response: ${response}`)
}

module.exports = {
  calcMass
}
