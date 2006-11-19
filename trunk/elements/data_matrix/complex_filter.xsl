<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="record_count" label="Records" numeric_sort="true"/>
            <attribute name="integer_count" label="Columns Integer" numeric_sort="true"/>
            <attribute name="float_count" label="Columns Float" numeric_sort="true"/>
            <attribute name="string_count" label="Columns String" numeric_sort="true"/>
            <attribute name="boolean_count" label="Columns Boolean" numeric_sort="true"/>
            <attribute name="date_count" label="Columns Date" numeric_sort="true"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="record_count" label="Záznamů" numeric_sort="true"/>
            <attribute name="integer_count" label="Sloupců Integer" numeric_sort="true"/>
            <attribute name="float_count" label="Sloupců Float" numeric_sort="true"/>
            <attribute name="string_count" label="Sloupců String" numeric_sort="true"/>
            <attribute name="boolean_count" label="Sloupců Boolean" numeric_sort="true"/>
            <attribute name="date_count" label="Sloupců Date" numeric_sort="true"/>
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->
      </attributes>

      <values>
        <xsl:apply-templates select="data_matrix" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>


  
  
  


  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">


    <xsl:element name="value">
      <xsl:for-each select="@*">
        <xsl:attribute name="{name()}">
          <xsl:value-of select="."/>
        </xsl:attribute>
      </xsl:for-each>
    </xsl:element>
		
	</xsl:template>


</xsl:stylesheet>
