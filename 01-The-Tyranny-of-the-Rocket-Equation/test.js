const { test } = require('tap')
const { calcMass } = require('./index')

test('test case 1', t => {
  t.plan(4)
  // For a mass of 12, divide by 3 and round down to get 4, then subtract 2 to get 2.
  t.equal(calcMass([12]), 2)
  // For a mass of 14, dividing by 3 and rounding down still yields 4, so the fuel required is also 2.
  t.equal(calcMass([14]), 2)
  // For a mass of 1969, the fuel required is 654.
  t.equal(calcMass([1969]), 654)
  // For a mass of 100756, the fuel required is 33583.
  t.equal(calcMass([100756]), 33583)
})
