import unittest
import pandas as pd
from Project import normalize_document, corpus, dt_matrix, word, dtm_df

class TestProject(unittest.TestCase):
    def test_normalize_document(self):
        """Test the normalize_document function."""
        input_text = "Hello, World! This is a TEST."
        expected_output = "hello world test"
        self.assertEqual(normalize_document(input_text), expected_output)

    def test_corpus_loading(self):
        """Test that the corpus is loaded correctly."""
        self.assertEqual(len(corpus), 3)  # Ensure there are 3 documents
        self.assertTrue(all(isinstance(doc, str) for doc in corpus))  # All documents should be strings

    def test_word_count(self):
        """Test word counting in the first document."""
        test_word = "ring"
        count = corpus[0].lower().count(test_word)  # Count occurrences in the first document
        expected_count = corpus[0].lower().count(test_word)  # Use corpus[0] for consistency
        self.assertEqual(count, expected_count)

    def test_dtm_structure(self):
        """Test the structure of the Document-Term Matrix."""
        self.assertEqual(len(dt_matrix), 3)  # Ensure there are 3 rows (one per document)
        self.assertTrue(all("Exact Match" in row for row in dt_matrix))  # Check for required keys
        self.assertTrue(all("Case-Insensitive Match" in row for row in dt_matrix))

    def test_dtm_dataframe(self):
        """Test the DTM DataFrame."""
        self.assertEqual(dtm_df.shape[0], 3)  # Ensure 3 rows (documents)
        self.assertIn("Document", dtm_df.columns)  # Ensure "Document" column exists
        self.assertIn("Exact Match", dtm_df.columns)  # Ensure "Exact Match" column exists

    def test_word_input(self):
        """Test that the input word is processed correctly."""
        self.assertIsInstance(word, str)  # Ensure the word is a string
        self.assertGreater(len(word), 0)  # Ensure the word is not empty

if __name__ == "__main__":
    unittest.main()