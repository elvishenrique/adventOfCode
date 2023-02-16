use std::io::stdin;

fn parse(line: &str) -> ((u32, u32), (u32, u32))
{
    let mut s = line.split(',');
    let mut a = s.next().unwrap().split('-');
    let mut b = s.next().unwrap().split('-');
    return ((a.next().unwrap().parse::<u32>().unwrap(), a.next().unwrap().parse::<u32>().unwrap()), (b.next().unwrap().trim_end().parse::<u32>().unwrap(), b.next().unwrap().trim_end().parse::<u32>().unwrap()));
}

fn contains(sections: ((u32, u32), (u32, u32))) -> bool
{
    return (std::cmp::min(sections.0.0, sections.1.0) == sections.0.0 && std::cmp::max(sections.0.1, sections.1.1) == sections.0.1) || (std::cmp::min(sections.0.0, sections.1.0) == sections.1.0 && std::cmp::max(sections.0.1, sections.1.1) == sections.1.1);
}

fn overlaps(sections: ((u32, u32), (u32, u32))) -> bool
{
    return (std::cmp::min(sections.0.0, sections.1.0) == sections.0.0 && sections.0.1 >= sections.1.0) || (std::cmp::min(sections.0.0, sections.1.0) == sections.1.0 && sections.1.1 >= sections.0.0);
}

fn main() {
    let (mut cont, mut over) = (0, 0);
    for _ in 0..1000
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        if contains(parse(&line))
        {
            cont += 1;
        }
        if overlaps(parse(&line))
        {
            over += 1;
        }
    }

    println!("{cont}, {over}");
}
