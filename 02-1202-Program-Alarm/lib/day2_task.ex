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
    computers = get_input_data()
    Day2.run(computers)
  end
end
