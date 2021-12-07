fn main() {
    let content = std::fs::read_to_string("input.txt").expect("Error");
    let input: Vec<i32> = content
        .split(',')
        .map(|x| x.parse::<i32>().unwrap())
        .collect();
    let max = input.iter().max().unwrap();
    let mut bestfuel = i32::MAX;
    let mut bestfuel2 = i32::MAX;

    for i in 0..*max {
        let mut total = 0;
        let mut total2 = 0;

        for c in input.iter() {
            total = total + (c - i).abs();
            total2 = total2 + (0..(c - i).abs() + 1).fold(0, |a, b| a + b)
        }

        if total < bestfuel {
            bestfuel = total;
        }
        if total2 < bestfuel2 {
            bestfuel2 = total2;
        }
    }
    println!("Part 1: {}", bestfuel);
    println!("Part 2: {}", bestfuel2);
}
