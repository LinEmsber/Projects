typedef long Align;

typedef union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
} Header;


static Header base;
static Header* freep = NULL;


/* knr_malloc: general-purpose storage allocator */
void * knr_malloc (unsigned nbytes)
{
	Header *   p;
	Header *   prevp;
	unsigned  nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(header) + 1;

        /* no free list yet */
	if ((prevp = freep) == NULL) {
		base.s.ptr = freeptr = prevptr = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits)             /* big enough */
		{
			if (p->s.size == nunits)           /* exactly */
				prevp->s.ptr = p->s.ptr;
			else                               /* allocate tail end */
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits
			}

			freep = prevp;
			return (void *)(p+1);
		}

		if (p == freep)                      /* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL;                     /* none left */
	}
}
