import { createClient } from 'https://cdn.jsdelivr.net/npm/@supabase/supabase-js/+esm'

// Supabase credentials
const supabaseUrl = "https://zzszxmzmumhbsqimjqal.supabase.co";
const supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Inp6c3p4bXptdW1oYnNxaW1qcWFsIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjI5MzAzMzgsImV4cCI6MjA3ODUwNjMzOH0.fEX9FTNWWWIj4rmnV2usDnlSyeVZBaFDSEEpof5Sokk";

const supabase = createClient(supabaseUrl, supabaseKey);

async function fetchData() {
  let { data, error } = await supabase
    .from('environment_Data')   // table name
    .select('*');

  if (error) {
    console.error("Error fetching data:", error);
    return;
  }

  const tableBody = document.querySelector("#data-table tbody");
  tableBody.innerHTML = ""; // Clear old rows

  data.forEach(row => {
    const tr = document.createElement("tr");
    tr.innerHTML = `
      <td>${row.temperature}</td>
      <td>${row.stetus}</td>
    `;
    tableBody.appendChild(tr);
  });
}

// Initial load
fetchData();
