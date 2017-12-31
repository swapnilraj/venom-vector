# Venom Vector
I was reading a blog on python arrays and I have been delving in C, so I thought
it would be cool to implement something similar in C, so it is a pythonic-array
in C yay!

# Warnings
I don't endorse this to work always, this probably has a lot of bugs.
So what is this, well think of this a Proof Of Concept, I had an idea and I just
bodged some code together, you could probably do a better implementation where
you use a `void*` instead of a `union` but I wanted to learn about unions.

# Memory Usage
The memory usage is insane, right now each Cell is `16 B`, totally not acceptable
in any valuable code, using a `void*` you could bring down the size of a Cell
to ~`12 B`, depending on the size of pointers on your platform.

# Efficientcy
This implementation is definitely not efficient in any sense, there are no bound
checks, I should probably add those. Other than that this gives you a pointer,
go crazy.

# Footer
I will try to find the link to the blog, it was something about the array
performance.
