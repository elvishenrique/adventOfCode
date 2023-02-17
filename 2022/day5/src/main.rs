use std::{io::stdin, collections::VecDeque};

fn parse_init(line: &str, stacks: &mut Vec<VecDeque<char>>)
{
    let mut index = 0;
    for c in line.chars()
    {
        if c == '['
        {
            // Found an element. index/4 is the stack we want to apply
            stacks[index/4].push_front(line.as_bytes()[index + 1] as char);
        }

        index += 1;
    }
}

// fn parse_inst(line: &str, stacks: &mut Vec<VecDeque<char>>)
// {
//     let move_pos = line.find("move ").unwrap();
//     let from_pos = line.find(" from ").unwrap();
//     let to_pos = line.find(" to ").unwrap();
//     let q = line.get((move_pos + 5)..from_pos).unwrap().parse::<usize>().unwrap();
//     let f = line.get((from_pos + 6)..to_pos).unwrap().parse::<usize>().unwrap() - 1;
//     let t = line.get((to_pos + 4)..).unwrap().trim_end().parse::<usize>().unwrap() - 1;
//     for _ in 0..q
//     {
//         let c = stacks[f].pop_back().unwrap();
//         stacks[t].push_back(c);
//     }
// }

fn parse_inst2(line: &str, stacks: &mut Vec<VecDeque<char>>)
{
    let move_pos = line.find("move ").unwrap();
    let from_pos = line.find(" from ").unwrap();
    let to_pos = line.find(" to ").unwrap();
    let q = line.get((move_pos + 5)..from_pos).unwrap().parse::<usize>().unwrap();
    let f = line.get((from_pos + 6)..to_pos).unwrap().parse::<usize>().unwrap() - 1;
    let t = line.get((to_pos + 4)..).unwrap().trim_end().parse::<usize>().unwrap() - 1;
    let mut aux = VecDeque::new();
    for _ in 0..q
    {
        let c = stacks[f].pop_back().unwrap();
        aux.push_back(c);
    }

    for _ in 0..q
    {
        let c = aux.pop_back().unwrap();
        stacks[t].push_back(c);
    }
}

fn main()
{
    let mut stacks = Vec::new();
    for _ in 0..9
    {
        let stack = VecDeque::<char>::new();
        stacks.push(stack.clone());
    }

    // Parse initial state
    for _ in 0..8
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        parse_init(&line, &mut stacks);
    }

    for _ in 0..2
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
    }

    for _ in 0..504
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        // parse_inst(&line, &mut stacks);
        parse_inst2(&line, &mut stacks);
    }

    for mut s in stacks
    {
        print!("{}", s.pop_back().unwrap());
    }

    print!("\n");
}
