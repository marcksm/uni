class NuspAndTypeCollum < ActiveRecord::Migration[5.1]
  def change
  	rename_column :users, :type, :usertype
  	change_column :users, :usertype, :boolean, :default => false
  	change_column_null :users, :usertype, false
  	add_index :users, :nusp, :unique => true
  end
end
