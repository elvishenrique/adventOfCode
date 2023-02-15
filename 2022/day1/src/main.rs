use std::{io::stdin, collections::BinaryHeap};

fn main()
{
    let mut cur = 0;
    let mut elves = BinaryHeap::new();
    for _ in 1..2237
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        let calories = line.trim_end().parse::<u32>();
        if calories.is_ok()
        {
            cur += calories.unwrap();
        }
        else {
            elves.push(cur);
            cur = 0;
        }
    }

    elves.push(cur);
    let (gold, silver, bronze) = (elves.pop().unwrap(), elves.pop().unwrap(), elves.pop().unwrap());
    println!("{}, {}", gold, gold + silver + bronze);
}
