defmodule Mix.Tasks.Day2 do
  use Mix.Task

  defp get_input_data() do
    File.read!("input.txt")
    |> String.split("\n")
    |> List.first()
    |> String.split(",")
    |> Enum.map(&String.to_integer/1)
  end

  def run(_) do
    computers =
      get_input_data()
      |> Enum.chunk_every(4)
      |> Enum.map(&parseAsIntcode/1)
    Day2.run(computers)
  end

  def parseAsIntcode([opcode, num1, num2, result]) do
    %Day2.IntcodeComputer{opcode: opcode, numbers: [num1, num2], result: result}
  end

  def parseAsIntcode(_tail), do: %Day2.IntcodeComputer{}
end
