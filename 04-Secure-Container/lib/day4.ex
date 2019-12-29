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

  defp has_proper_double?(num) do
    num
    |> Integer.digits
    |> Enum.chunk_by(& &1)
    |> Enum.any?(&(Enum.count(&1) === 2))
  end

  def first_part_rules(num) do
    has_double?(num) and never_decrease?(num)
  end

  def second_part_rules(num) do
    first_part_rules(num) and has_proper_double?(num)
  end

  def process_range([from, to], func) do
    for(x <- from..to, do: x)
    |> Enum.filter(fn n -> func.(n) end)
    |> Enum.count
  end

  def main() do
    res =
      get_input_data()
      |> process_range(&first_part_rules/1)

    res2 =
      get_input_data()
      |> process_range(&second_part_rules/1)

    IO.puts "Part one: #{res}"
    IO.puts "Part two: #{res2}"
  end
end
