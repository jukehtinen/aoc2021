use std::fs;

fn main() {
    let content = fs::read_to_string("input.txt").expect("Error");
    let input: Vec<i32> = content
        .split(',')
        .map(|x| x.parse::<i32>().unwrap())
        .collect();

    // Part 1
    let mut data = input.to_vec();
    for _t in 0..80 {
        let mut addnew = 0;
        for i in data.iter_mut() {
            *i = *i - 1;
            if *i == -1 {
                *i = 6;
                addnew = addnew + 1;
            }
        }
        for _t in 0..addnew {
            data.push(8);
        }
    }
    println!("Part 1: {}", data.len());

    // Part 2
    let mut days: [i64; 9] = [0; 9];
    for i in input.iter() {
        days[*i as usize] = days[*i as usize] + 1;
    }
    for _t in 0..256 {
        let addnew = days[0];
        for i in 1..days.len() {
            days[i - 1] = days[i];
        }
        days[6] = days[6] + addnew;
        days[8] = addnew;
    }

    let mut sum = 0;
    for i in 0..days.len() {
        sum = sum + days[i];
    }

    println!("Part 2: {}", sum);
}
