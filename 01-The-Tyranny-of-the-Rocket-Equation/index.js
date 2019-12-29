const input = require('./input')

const calcFuel = mass => Math.floor(mass / 3) - 2

const calcFullFuel = (mass, sum) => {
  const value = calcFuel(mass)

  if (value <= 0) {
    return sum
  }
  return calcFullFuel(value, sum + value)
}

function calcMass(input, calc = calcFuel) {
  return input
    .map(calc)
    .reduce((prev, curr) => prev + curr, 0)
}

function main() {
  const response = calcMass(input)
  console.log(`Part one: ${response}`)
  const response2 = calcMass(input, n => calcFullFuel(n, 0))
  console.log(`Part two: ${response2}`)
}

main()

module.exports = {
  calcMass
}
