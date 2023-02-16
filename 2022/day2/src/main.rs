use std::io::stdin;

fn rps(theirs: &str, yours: &str) -> i32
{
    match yours
    {
        "X" =>
        {
            match theirs
            {
                "A" => return 4,
                "B" => return 1,
                "C" => return 7,
                _ => panic!()
            }
        },
        "Y" =>
        {
            match theirs
            {
                "A" => return 8,
                "B" => return 5,
                "C" => return 2,
                _ => panic!()
            }
        },
        "Z" =>
        {
            match theirs
            {
                "A" => return 3,
                "B" => return 9,
                "C" => return 6,
                _ => panic!()
            }
        },
        _ => panic!()
    }
}

fn revert_rps(theirs: &str, result: &str) -> i32
{
    match theirs
    {
        "A" =>
        {
            match result
            {
                "X" => return 3,
                "Y" => return 4,
                "Z" => return 8,
                _ => panic!()
            }
        },
        "B" =>
        {
            match result
            {
                "X" => return 1,
                "Y" => return 5,
                "Z" => return 9,
                _ => panic!()
            }
        },
        "C" =>
        {
            match result
            {
                "X" => return 2,
                "Y" => return 6,
                "Z" => return 7,
                _ => panic!()
            }
        },
        _ => panic!()
    }
}

fn main() {
    let (mut points, mut real_points) = (0, 0);
    for _ in 0..2500
    {
        let mut line = String::new();
        stdin().read_line(&mut line).unwrap();
        let mut iter = line.split_ascii_whitespace();
        let (theirs, yours) = (iter.next().unwrap(), iter.next().unwrap());
        points += rps(theirs, yours);
        real_points += revert_rps(theirs, yours);
    }

    println!("{}", points);
    println!("{}", real_points);
}
