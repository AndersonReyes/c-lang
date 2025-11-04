import glob
import os
import re


dirname = os.path.dirname(__file__)

template = """
#include <stdio.h>

{defs}


typedef void (*fn) (void);

void runner(const char* name, fn func, const char* file) {{
    func();

    printf("%s:%s PASSED\\n", file, name);
}}

int main(void) {{

    printf("\\n======== RUNNING TESTS ========\\n");

    {calls}

    return 0;
}}
"""


if __name__ == "__main__":
    regex = re.compile("void.*(void).*{.*")
    lines = []
    for f in glob.glob(os.path.join(dirname, "**/*.c"), recursive=True):
        with open(f) as fp:

            for line in fp.readlines():
                if regex.match(line):
                    line = line.replace("void ", "").replace(
                        "(void)", "").replace("{", "").strip()
                    lines.append({
                        "name": line, "file": os.path.basename(f)})

    defs = "\n".join([f"""void {k["name"]}(void);""" for k in lines])
    calls = "\n".join(
        [f"""runner("{k["name"]}", {k["name"]}, "{k["file"]}");""" for k in lines])

    with open(os.path.join(dirname, "all_tests.c"), "+w") as f:
        f.write(template.format(defs=defs, calls=calls))
