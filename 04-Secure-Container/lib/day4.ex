defmodule Day4 do
  @moduledoc """
  Documentation for Day4.
  """

  def get_input_data() do
    [123257, 647015]
  end

  defp has_double?(num) do
    num
    |> Integer.digits
    |> Enum.chunk_by(& &1)
    |> Enum.any?(&(Enum.count(&1) >= 2))
  end

  defp never_decrease?(num) do
    digits = Integer.digits(num)

    digits === Enum.sort(digits)
  end

  def assert_rules(num) do
    has_double?(num) and never_decrease?(num)
  end

  def process_range([from, to]) do
    for(x <- from..to, do: x)
    |> Enum.filter(&assert_rules/1)
    |> Enum.count
  end

  def main() do
    res =
      get_input_data()
      |> process_range

    IO.puts res
  end
end
