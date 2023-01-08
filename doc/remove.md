# Details On GraphicsBuffer::Remove()

When the Remove() function is called, instead of calling a function from the underlying graphics API to change the data of the inner buffer, a MemorySection is added to the list of free memories.

This approach is similiar to what operating systems use when you delete a file. Instead of filling the hard drive with zeros, the part of memory the file is stored in becomes marked as available. New files will override the deleted file.

find memory section on left
    found: can extend?
        yes: extend
        no: find memory section on right
            found: can extend?
                yes: extend
                no: create memory section
            not found: create memory section
    not found: goto 10

## Algorithm
Let [offset] and [size] be the arguments of Remove()

Remove() attempts to find the first MemorySection with an offset that is at or after [offset].

If GraphicsBuffer doesn't have any MemorySections, a new one is created at the [offset], and will span [size] bytes. The size of the MemorySection may be truncated to fit the size of the GraphicsBuffer.

[x500][100][200][x200]
The MemorySection at [offset]

[1000]
[500][500]

## Tables

| Left columns  | Right columns |
| ------------- |:-------------:|
| left foo      | right foo     |
| left bar      | right bar     |
| left baz      | right baz     |

## Blocks of code

```
let message = 'Hello world';
alert(message);
```

## Inline code

This web site is using `markedjs/marked`.
