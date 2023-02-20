use std::io::stdin;

fn check(index: usize, line: &str) -> bool
{
    //for i in 0..3
    for i in 0..13
    {
        //for j in (i + 1)..4
        for j in (i + 1)..14
        {
            if line.get((index + i)..(index + i + 1)).unwrap() == line.get((index + j)..(index + j + 1)).unwrap()
            {
                return false;
            }
        }
    }

    return true;
}

fn main() {
    let mut line = String::new();
    stdin().read_line(&mut line).unwrap();
    //for i in 0..line.len() - 3
    for i in 0..line.len() - 13
    {
        if check(i, &line)
        {
            //println!("{}", i + 4);
            println!("{}", i + 14);
            break;
        }
    }
}
