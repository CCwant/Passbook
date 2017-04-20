public class Adler32 {

	private static final int BASE = 65521;

	private int checksum; // we do all in int.

	public Adler32() {
		reset();
	}

	public void reset() {
		checksum = 1; // Initialize to 1
	}

	public void update(int bval) {
		// We could make a length 1 byte array and call update again, but I
		// would rather not have that overhead
		int s1 = checksum & 0xffff;
		int s2 = checksum >>> 16;

		s1 = (s1 + (bval & 0xFF)) % BASE;
		s2 = (s1 + s2) % BASE;

		checksum = (s2 << 16) + s1;
	}

	public void update(byte[] buffer) {
		update(buffer, 0, buffer.length);
	}

	public void update(byte[] buf, int off, int len) {
		// (By Per Bothner)
		int s1 = checksum & 0xffff;
		int s2 = checksum >>> 16;

		while (len > 0) {
			// We can defer the modulo operation:
			// s1 maximally grows from 65521 to 65521 + 255 * 3800
			// s2 maximally grows by 3800 * median(s1) = 2090079800 < 2^31
			int n = 3800;
			if (n > len)
				n = len;
			len -= n;
			while (--n >= 0) {
				s1 = s1 + (buf[off++] & 0xFF);
				s2 = s2 + s1;
			}
			s1 %= BASE;
			s2 %= BASE;
		}

		/*
		 * Old implementation, borrowed from somewhere: int n;
		 * 
		 * while (len-- > 0) {
		 * 
		 * s1 = (s1 + (bs[offset++] & 0xff)) % BASE; s2 = (s2 + s1) % BASE; }
		 */

		checksum = (s2 << 16) | s1;
	}

	/**
	 * Returns the Adler32 data checksum computed so far.
	 */
	public long getValue() {
		return (long) checksum & 0xffffffffL;
	}

}
