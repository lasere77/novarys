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

    pub fn  im(&mut self, value: u8) {
        self.a.u_byte = value;
    }
}
