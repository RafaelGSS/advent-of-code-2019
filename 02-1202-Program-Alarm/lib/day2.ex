defmodule Day2 do
  defmodule IntcodeComputer do
    defstruct opcode: nil, numbers: [0, 0], result: 0
  end

  def run(computers) do
    response =
      computers
      |> Enum.map(&solveComputeOperation/1)

    require IEx; IEx.pry
  end

  def solveComputeOperation(%IntcodeComputer{opcode: 1} = computer) do
    %IntcodeComputer{computer | result: Enum.sum(computer.numbers)}
  end

  def solveComputeOperation(%IntcodeComputer{opcode: 2} = computer) do
    %IntcodeComputer{computer | result: Enum.reduce(computer.numbers, &(&1 * &2))}
  end

  def solveComputeOperation(%IntcodeComputer{opcode: 99} = computer) do
    -1
  end

  def solveComputeOperation(_tail), do: -2

end
