#!/usr/bin/env python3
"""
HTML to Markdown Converter
Converts HTML files or HTML strings to Markdown format.
"""

import os
import sys
import argparse
from pathlib import Path
import html2text
from bs4 import BeautifulSoup


def html_to_markdown(html_content, baseurl=None, bodywidth=80, ignore_links=False,
                     ignore_images=False, ignore_emphasis=False, single_line_break=False):
    """
    Convert HTML content to Markdown using html2text.

    Args:
        html_content (str): HTML content to convert
        baseurl (str, optional): Base URL for relative links
        bodywidth (int): Maximum width of text lines
        ignore_links (bool): Whether to ignore links
        ignore_images (bool): Whether to ignore images
        ignore_emphasis (bool): Whether to ignore emphasis (bold, italic)
        single_line_break (bool): Whether to use single line breaks

    Returns:
        str: Converted Markdown content
    """
    # Create html2text converter with options
    converter = html2text.HTML2Text()

    # Configure converter options
    converter.body_width = bodywidth
    converter.ignore_links = ignore_links
    converter.ignore_images = ignore_images
    converter.ignore_emphasis = ignore_emphasis
    converter.single_line_break = single_line_break
    converter.protect_links = True
    converter.mark_code = True

    if baseurl:
        converter.baseurl = baseurl

    # Convert HTML to Markdown
    markdown_content = converter.handle(html_content)

    return markdown_content


def clean_html(html_content):
    """
    Clean and prettify HTML content using BeautifulSoup.

    Args:
        html_content (str): Raw HTML content

    Returns:
        str: Cleaned HTML content
    """
    soup = BeautifulSoup(html_content, 'html.parser')

    # Remove script and style tags
    for script in soup(["script", "style"]):
        script.decompose()

    # Get text and clean it
    text = soup.get_text()

    # Break into lines and remove leading/trailing space on each
    lines = (line.strip() for line in text.splitlines())

    # Break multi-headlines into a line each
    chunks = (phrase.strip() for line in lines for phrase in line.split("  "))

    # Drop blank lines
    text = '\n'.join(chunk for chunk in chunks if chunk)

    return text


def convert_file(input_file, output_file=None, options=None):
    """
    Convert an HTML file to Markdown.

    Args:
        input_file (str): Path to input HTML file
        output_file (str, optional): Path to output Markdown file
        options (dict, optional): Conversion options

    Returns:
        str: Converted Markdown content
    """
    if options is None:
        options = {}

    # Read input file
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            html_content = f.read()
    except Exception as e:
        print(f"Error reading input file: {e}")
        return None

    # Convert to Markdown
    markdown_content = html_to_markdown(
        html_content,
        baseurl=options.get('baseurl'),
        bodywidth=options.get('bodywidth', 80),
        ignore_links=options.get('ignore_links', False),
        ignore_images=options.get('ignore_images', False),
        ignore_emphasis=options.get('ignore_emphasis', False),
        single_line_break=options.get('single_line_break', False)
    )

    # Write output file if specified
    if output_file:
        try:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(markdown_content)
            print(f"Successfully converted {input_file} to {output_file}")
        except Exception as e:
            print(f"Error writing output file: {e}")

    return markdown_content


def convert_directory(input_dir, output_dir=None, options=None):
    """
    Convert all HTML files in a directory to Markdown.

    Args:
        input_dir (str): Path to input directory containing HTML files
        output_dir (str, optional): Path to output directory for Markdown files
        options (dict, optional): Conversion options
    """
    input_path = Path(input_dir)

    if not input_path.exists() or not input_path.is_dir():
        print(f"Error: {input_dir} is not a valid directory")
        return

    # Create output directory if specified
    if output_dir:
        output_path = Path(output_dir)
        output_path.mkdir(parents=True, exist_ok=True)

    # Find all HTML files
    html_files = list(input_path.glob("**/*.html")) + list(input_path.glob("**/*.htm"))

    if not html_files:
        print(f"No HTML files found in {input_dir}")
        return

    print(f"Found {len(html_files)} HTML file(s)")

    for html_file in html_files:
        # Determine output file path
        if output_dir:
            # Preserve directory structure
            relative_path = html_file.relative_to(input_path)
            output_file = Path(output_dir) / relative_path.with_suffix('.md')
            output_file.parent.mkdir(parents=True, exist_ok=True)
        else:
            # Save in same directory with .md extension
            output_file = html_file.with_suffix('.md')

        # Convert file
        convert_file(str(html_file), str(output_file), options)


def main():
    """Main function to handle command line arguments."""
    parser = argparse.ArgumentParser(
        description='Convert HTML files to Markdown format',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s input.html                  # Convert single file, save as input.md
  %(prog)s input.html -o output.md     # Convert to specific output file
  %(prog)s input.html --bodywidth 0    # Disable line wrapping
  %(prog)s -d ./html_files/            # Convert all HTML files in directory
  %(prog)s -d ./html_files/ -o ./markdown/  # Convert directory with output dir
  %(prog)s input.html --ignore-links   # Convert without links
  %(prog)s input.html --baseurl https://example.com  # Set base URL for relative links
        """
    )

    # Input options
    input_group = parser.add_mutually_exclusive_group(required=True)
    input_group.add_argument('input_file', nargs='?', help='Input HTML file')
    input_group.add_argument('-d', '--directory', help='Directory containing HTML files')

    # Output options
    parser.add_argument('-o', '--output', help='Output file (for single file) or directory (for batch conversion)')

    # Conversion options
    parser.add_argument('--baseurl', help='Base URL for relative links')
    parser.add_argument('--bodywidth', type=int, default=80, help='Maximum width of text lines (0 for no wrapping)')
    parser.add_argument('--ignore-links', action='store_true', help='Ignore links in conversion')
    parser.add_argument('--ignore-images', action='store_true', help='Ignore images in conversion')
    parser.add_argument('--ignore-emphasis', action='store_true', help='Ignore emphasis (bold, italic)')
    parser.add_argument('--single-line-break', action='store_true', help='Use single line breaks')

    args = parser.parse_args()

    # Prepare options dictionary
    options = {
        'baseurl': args.baseurl,
        'bodywidth': args.bodywidth,
        'ignore_links': args.ignore_links,
        'ignore_images': args.ignore_images,
        'ignore_emphasis': args.ignore_emphasis,
        'single_line_break': args.single_line_break
    }

    # Handle directory conversion
    if args.directory:
        convert_directory(args.directory, args.output, options)

    # Handle single file conversion
    elif args.input_file:
        # Determine output file
        if args.output:
            output_file = args.output
        else:
            # Default: replace extension with .md
            input_path = Path(args.input_file)
            output_file = str(input_path.with_suffix('.md'))

        convert_file(args.input_file, output_file, options)


if __name__ == "__main__":
    # Check if required packages are installed
    try:
        import html2text
        from bs4 import BeautifulSoup
    except ImportError as e:
        print("Error: Required packages not installed.")
        print("Please install them using:")
        print("  pip install html2text beautifulsoup4")
        sys.exit(1)

    main()
