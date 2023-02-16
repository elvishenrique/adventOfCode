use std::io::stdin;

fn both_halves(items : &str) -> u32
{
    let n = items.chars().count();
    let first_half = items.get(..n/2).unwrap();
    let second_half = items.get(n/2..).unwrap();
    for c in first_half.chars()
    {
        if second_half.contains(c)
        {
            if c.is_lowercase()
            {
                return c as u32 - 'a' as u32 + 1;
            }
            else
            {
                return c as u32 - 'A' as u32 + 27;
            }
        }
    }

    return 0;
}

fn badge(elves : &[String]) -> u32
{
    let n = elves.len();
    if n != 3
    {
        panic!();
    }

    let (a, b, c) = (&elves[0], &elves[1], &elves[2]);
    for i in a.chars()
    {
        if b.contains(i) && c.contains(i)
        {
            if i.is_lowercase()
            {
                return i as u32 - 'a' as u32 + 1;
            }
            else
            {
                return i as u32 - 'A' as u32 + 27;
            }
        }
    }

    return 0;
}


fn main() {
    let mut pri = 0;
    let mut rucks = Vec::new();
    for _ in 0..300
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        pri += both_halves(&line);
        rucks.push(line.clone());
    }

    let mut bad = 0;
    for i in 0..100
    {
        let group = rucks.get((3 * i)..(3 * i + 3)).unwrap();
        bad += badge(&group);
    }

    println!("{pri}, {bad}");
}
