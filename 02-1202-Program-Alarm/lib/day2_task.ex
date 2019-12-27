defmodule Mix.Tasks.Day2 do
  use Mix.Task

  defp get_input_data() do
    File.read!("input.txt")
    |> String.split("\n")
    |> List.first()
    |> String.split(",")
    |> Enum.map(&String.to_integer/1)
  end

  defp solve(input_data, noun, verb) do
    input_data
    |> List.replace_at(1, noun)
    |> List.replace_at(2, verb)
    |> Day2.run()
    |> Enum.at(0)
  end

  def part_one() do
    solve(get_input_data(), 12, 2)
  end


  def part_two() do
    input_data = get_input_data()

    {noun, verb} = 
      for(noun <- 0..99, verb <- 0..99, do: {noun, verb})
      |> Enum.find(fn {noun, verb} -> 
        solve(input_data, noun, verb) == 19690720 
      end)

    100 * noun + verb
  end

 @shortdoc "Execute operation based on args (1- part one / 2- part two)"
  def run([part]) do
    case part do
      "1" ->
        IO.puts part_one()
      "2" ->
        IO.puts part_two()
    end
  end
end
