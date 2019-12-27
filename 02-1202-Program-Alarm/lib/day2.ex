defmodule Day2 do
  defmodule IntcodeComputer do
    defstruct opcode: nil, numbers: [0, 0], result_position: 0
  end

  def run(computers) do
    solveComputeOperation(computers, parseFirstAsIntcode(computers))
  end

  def solveComputeOperation(computers, computer, current_pos \\ 0)

  def solveComputeOperation(computers, %IntcodeComputer{opcode: 99}, _current_pos), do: computers
  def solveComputeOperation(computers, %IntcodeComputer{} = computer, current_pos) do
    [first_value, second_value] = Enum.map(computer.numbers, &Enum.at(computers, &1))
    new_pos = current_pos + 4
    case computer.opcode do
      1 ->
        List.update_at(computers, computer.result_position, fn _ -> _ = first_value + second_value end)
        |> (&(solveComputeOperation(&1, parseFirstAsIntcode(Enum.drop(&1, new_pos)), new_pos))).()
      2 ->
        List.update_at(computers, computer.result_position, fn _ -> _ = first_value * second_value end)
        |> (&(solveComputeOperation(&1, parseFirstAsIntcode(Enum.drop(&1, new_pos)), new_pos))).()
    end
  end

  def parseFirstAsIntcode(computers) do
    if length(computers) < 4 do
      parseAsIntcode([99, nil, nil, nil])
    else
      [opcode, num1, num2, result_position | _tail] = computers
      parseAsIntcode([opcode, num1, num2, result_position])
    end 
  end

  def parseAsIntcode([opcode, num1, num2, result_position]) do
    %IntcodeComputer{opcode: opcode, numbers: [num1, num2], result_position: result_position}
  end
end
