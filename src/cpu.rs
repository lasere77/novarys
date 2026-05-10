/*
    Cpu
*/
#[repr(C)]
pub union Byte {
    i_byte: i8,
    u_byte: u8,
}

pub struct Cpu {
    pub nv:     u8,
    pub a:      Byte,
    pub c:      Byte,
    pub d:      Byte,
    pub r:      Byte,
    pub f:      Byte,
    pub x:      Byte,
    pub reg_in:     Byte,
    pub reg_out:    Byte,
}

impl Cpu {
    pub fn init() -> Self
    {
        Self {
            nv: (0), a: (Byte {u_byte: 0}), c: (Byte {u_byte: 0}), d: (Byte {u_byte: 0}),
            r: (Byte {u_byte: 0}), f: (Byte {u_byte: 0}), x: (Byte {u_byte: 0}),
            reg_in: (Byte {u_byte: 0}), reg_out: (Byte {u_byte: 0})
        }
    }

    pub fn info(&self) {
        println!("tick: {}\n----", self.nv);
        unsafe {
            println!("IN {}", self.reg_in.i_byte);
            println!("reg A {}", self.a.i_byte);
            println!("reg C {}", self.c.i_byte);
            println!("reg D {}", self.d.i_byte);
            println!("reg R {}", self.r.i_byte);
            println!("reg F {}", self.f.i_byte);
            println!("reg X {}", self.x.i_byte);
            println!("OUT {}", self.reg_out.i_byte);
        }
        print!("----")
    }

    pub fn  im(&mut self, value: u8) {
        self.a.u_byte = value;
    }

    pub fn alu(&mut self, instruction: u8) {
        let logic_gate = instruction & 0b00000111;
        match logic_gate {
            0 => self.r.i_byte = unsafe {self.c.i_byte | self.d.i_byte},
            1 => self.r.i_byte = unsafe {!(self.c.i_byte & self.d.i_byte)},
            2 => self.r.i_byte = unsafe {!(self.c.i_byte | self.d.i_byte)},
            3 => self.r.i_byte = unsafe {self.c.i_byte & self.d.i_byte},
            4 => self.r.i_byte = unsafe {self.c.i_byte + self.d.i_byte},
            5 => self.r.i_byte = unsafe {self.c.i_byte - self.d.i_byte},
            _ => todo!(),
        }
    }
}
